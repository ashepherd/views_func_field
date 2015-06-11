<?php

/**
 * @file
 * views_handler_views_func_field_function.inc
 */

/**
 * Field handler to display the results of a function.
 */
class views_func_field_handler_function extends views_handler_field_custom {

  function query() {
    // Do nothing.
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['views_func_field_function'] = array(
      'default' => '',
      'translatable' => FALSE,
    );

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $functions = array();
    foreach (module_implements('views_func_field_function') as $module) {
      $result = module_invoke($module, 'views_func_field_function');
      foreach($result as $function) {
	$functions[$function] = $module . ': ' . $function;
      }
    }
  	
    $form['views_func_field_function'] = array(
      '#weight' => 0,
      '#title' => t('Available Functions'),
      '#options' => $functions,
      '#type' => 'select',
      '#default_value' => $this->options['views_func_field_function'],
      '#description' => t('Choose the function to execute. <i>Declare a function by implementing hook_views_func_field_function()</i>.'),
    );
    $form['alter']['text']['#title'] = t('Function Arguments');
    $form['alter']['text']['#description'] = t('Enter one argument per line. You may use "Replacement Patterns" for function arguments.');
  }

  /**
   * Perform an advanced text render for the item.
   *
   * This is separated out as some fields may render lists, and this allows
   * each item to be handled individually.
   */
  function render_text($alter) {

    // The function to execute.
    $function = $this->options['views_func_field_function'];
    if (function_exists($function)) {

      // The function's arguments.
      $args = array();

      // Parse the provided arguments, substituting any token values.
      $tokens = $this->get_render_tokens($alter);
      $text_arguments = $this->render_altered($alter, $tokens);

      // Turn the text arguments into an array of arguments.     
      if (!empty($text_arguments)) {
        $args = explode("\n", $text_arguments);
        // Trim values so no argument has any surrounding whitespace.
        foreach($args as $i => $arg) {
          $args[$i] = trim($arg);
        }
      }

      // Call the function.
      $value = call_user_func_array($function, $args);

      // Return the function's value as a string.
      return strval($value);
    }
    else {
      // Display error message, but do not repeat the message.
      drupal_set_message(t('Could not execute the function: %func', array('%func' => $function)), 'error', FALSE);
    }

    // Return an empty string if you got this far.
    return '';
  }
}
