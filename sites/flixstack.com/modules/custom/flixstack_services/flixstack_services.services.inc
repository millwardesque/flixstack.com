<?php

/**
 * @file
 * Service routines for the flixstack_services module.
 */

/**
 * Checks to see if a certain movie ID is in the user's stack.
 *
 * @param $operation
 *  The operation being called.
 * @param $data
 *  Data from the service call.
 *
 * @return An object containing one key (is_queued), a boolean indicating whether the ID is in the queue.
 */
function _flixstack_services_is_in_stack($operation, $data) {
  $id = $data['id'];

  $return = new stdClass();
  $return->is_queued = _flixstack_services_is_in_stack_helper($id);
  $return->id = $id;

  return $return;
}

/**
 * Checks to see if a certain movie ID is watched.
 *
 * @param $operation
 *  The operation being called.
 * @param $data
 *  Data from the service call.
 *
 * @return An object containing one key (is_watched), a boolean indicating whether the ID has been watched by the user.
 */
function _flixstack_services_is_watched($operation, $data) {
  $id = $data['id'];

  $return = new stdClass();
  $return->is_watched = _flixstack_services_is_watched_helper($id);
  $return->id = $id;

  return $return;
}

/**
 * Checks to see if multiple movie IDs are in the user's stack.
 *
 * @param $operation
 *  The operation being called.
 * @param $data
 *  Data from the service call.
 *
 * @return An object containing a mapping from each ID to true (for queued) or false (for not queued).
 */
function _flixstack_services_are_in_stack ($operation, $data) {
  $ids = explode('||', $data['ids']);

  $return = new stdClass();
  $return->ids = array();
  foreach ($ids as $id) {
    $return->ids[$id] = _flixstack_services_is_in_stack_helper($id);
  }

  return $return;
}

/**
 * Gets the URL pattern
 *
 * @param $operation
 *  The operation being called.
 * @param $data
 *  Data from the service call.
 *
 * @return An object containing a single key (pattern). This will contain the pattern if the video type was found, or an empty string if not.
 */
function _flixstack_services_get_url_pattern($operation, $data) {
  $video_type = $data['video_type'];
  $pattern = '';

  if ('netflix' == $video_type) {
    $pattern = variable_get('flixstack_core_url_match_pattern_netflix', FLIXSTACK_CORE_URL_MATCH_PATTERN_NETFLIX_DEFAULT);
  }

  $return = new stdClass();
  $return->pattern = $pattern;

  return $return;
}

/**
 * Adds an video to the stack.
 *
 * If the video ID doesn't already exist, a new entry is created for it in the system.
 *
 * @param $operation
 *  The operation being called.
 * @param $data
 *  Data from the service call.
 *
 * @return An object describing the node that was added.
 */
function _flixstack_services_add_to_stack($operation, $data) {
  $return = new stdClass();

  // Get the video node
  $video_id = $data['video_id'];
  $video_nodes = _flixstack_services_find_by_id($video_id);
  $video_node = null;

  // If there's no node for the video, create one.
  if (empty($video_nodes)) {
    $node = new stdClass();
    $node->title = $data['title'];
    $node->type = 'netflix_video';
    $node->uid = 1; // All videos created belong to admin.
    node_save($node);
    $wrapper = entity_metadata_wrapper('node', $node);

    // Set the video ID.
    $wrapper->field_video_id->set($data['video_id']);

    // Download and attach the movie image.
    $image_url = $data['image_url'];
    if ($image_url) {
      $image_data = file_get_contents($image_url);
      if ($image_data) {
        $image_filename = 'public://video-images' . substr($image_url, strrpos($image_url, '/'));
        $file = file_save_data($image_data, $image_filename);
        if ($file) {
          $wrapper->field_video_image = array('fid' => $file->fid);
        }
      }
    }

    // Save the node contents and reload the node itself.
    $wrapper->save();
    $video_node = node_load($node->nid);    
  }
  else {
    $video_node = reset($video_nodes);
  }

  // Add to the the stack and mark as unwatched
  if ($video_node) {
    $in_my_stack = flag_get_flag('in_my_stack');
    $in_my_stack->flag('flag', $video_node->nid);
    $is_watched = flag_get_flag('watched_video');
    $is_watched->flag('unflag', $video_node->nid);

    // Output
    $return->node = $video_node;
    $return->is_watched = $is_watched->is_flagged($video_node->nid);
    $return->in_my_stack = $in_my_stack->is_flagged($video_node->nid);
  }

  return $return;
}

/**
 * Removes a video from the user's stack.
 *
 * @param $operation
 *  The operation being called.
 * @param $data
 *  Data from the service call.
 *
 * @return An object containing a single key (was_removed). This will be true if a matching node was found, 
 *   or false if not.
 */
function _flixstack_services_remove_from_stack($operation, $data) {
  $was_removed = false;

  // Get the video node
  $video_id = $data['video_id'];
  $video_nodes = _flixstack_services_find_by_id($video_id);

  // Mark as watched
  if (!empty($video_nodes)) {
    $video_node = reset($video_nodes);
    $flag = flag_get_flag('in_my_stack');
    $flag->flag('unflag', $video_node->nid);
    $was_removed = true;
  }
  
  // Output
  $return = new stdClass();
  $return->was_removed = $was_removed;

  return $return;
}

/**
 * Marks a video as watched.
 *
 * @param $operation
 *  The operation being called.
 * @param $data
 *  Data from the service call.
 *
 * @return An object containing a single key (is_watched). This will be true if a matching node was found, 
 *   or false if not.
 */
function _flixstack_services_mark_as_watched($operation, $data) {
  $is_watched = false;

  // Get the video node
  $video_id = $data['video_id'];
  $video_nodes = _flixstack_services_find_by_id($video_id);

  // Mark as watched
  if (!empty($video_nodes)) {
    $video_node = reset($video_nodes);
    $flag = flag_get_flag('watched_video');
    $flag->flag('flag', $video_node->nid);
    $is_watched = true;
  }
  
  // Output
  $return = new stdClass();
  $return->is_watched = $is_watched;

  return $return;
}
