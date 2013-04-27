<?php
/**
 * @file
 * flixstack_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function flixstack_core_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "services" && $api == "services") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function flixstack_core_views_api() {
  return array("api" => "3.0");
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
  );
  return $items;
}
