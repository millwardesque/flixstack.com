<?php
/**
 * @file
 * flixstack_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function flixstack_core_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function flixstack_core_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function flixstack_core_flag_default_flags() {
  $flags = array();
  // Exported flag: "In My Stack".
  $flags['in_my_stack'] = array(
    'content_type' => 'node',
    'title' => 'In My Stack',
    'global' => 0,
    'types' => array(
      0 => 'netflix_video',
    ),
    'flag_short' => 'Add To Stack',
    'flag_long' => '',
    'flag_message' => '[node:title] has been added to your stack.',
    'unflag_short' => 'Remove from stack',
    'unflag_long' => '',
    'unflag_message' => '[node:title] has been removed from your stack.',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 2,
      ),
      'unflag' => array(
        0 => 2,
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_contextual_link' => 0,
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'flixstack_core',
    'locked' => array(
      0 => 'name',
    ),
  );
  // Exported flag: "Watched".
  $flags['watched_video'] = array(
    'content_type' => 'node',
    'title' => 'Watched',
    'global' => 0,
    'types' => array(
      0 => 'netflix_video',
    ),
    'flag_short' => 'Mark as watched',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Mark as unwatched',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 2,
      ),
      'unflag' => array(
        0 => 2,
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => 'own',
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_contextual_link' => 0,
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'flixstack_core',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}

/**
 * Implements hook_node_info().
 */
function flixstack_core_node_info() {
  $items = array(
    'netflix_video' => array(
      'name' => t('Netflix Video'),
      'base' => 'node_content',
      'description' => t('A Netflix video in the queue'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'webform' => array(
      'name' => t('Webform'),
      'base' => 'node_content',
      'description' => t('Create a new form or questionnaire accessible to users. Submission results and statistics are recorded and accessible to privileged users.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
