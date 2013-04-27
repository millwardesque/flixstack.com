<?php
/**
 * @file
 * flixstack_services_config.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function flixstack_services_config_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'flixstack_core_url_match_pattern_netflix';
  $strongarm->value = '/movieid=([0-9]+?)&/';
  $export['flixstack_core_url_match_pattern_netflix'] = $strongarm;

  return $export;
}
