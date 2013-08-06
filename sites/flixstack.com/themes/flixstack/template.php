<?php

/**
 * @file
 * Routines and overrides for the flixstack theme
 */

/**
 * Implements hook_preprocess_html().
 */
function flixstack_preprocess_html(&$variables) {
  // First, we must set up an array
  $element = array(
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width,initial-scale=1,minimum-scale=1,maximum-scale=1',
    ),
  );
  drupal_add_html_head($element, 'meta-viewport');
}
