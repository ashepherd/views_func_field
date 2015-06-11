<?php

/**
 * @file
 * views_func_field.api.php
 * Hooks provided by Views Function Field.
 */

/**
 * Declare a function as callable by Views.
 *
 * Return an array of function names that may be called by Views
 * to supply the value for a field. 
 *
 * @see views_func_field/views/handlers/views_handler_views_func_field_function.inc
 *
 * @return $functions
 *   An Array of function names
 */
function hook_views_func_field_function() {
  return array(
    'drupal_get_title',
  );
}
