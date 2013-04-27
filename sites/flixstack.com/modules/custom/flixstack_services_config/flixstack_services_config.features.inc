<?php
/**
 * @file
 * flixstack_services_config.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function flixstack_services_config_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function flixstack_services_config_image_default_styles() {
  $styles = array();

  // Exported image style: service_view_thumbnail.
  $styles['service_view_thumbnail'] = array(
    'name' => 'service_view_thumbnail',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 45,
          'height' => 64,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
