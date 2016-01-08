<?php
/**
 * Admin form callback.
 */
 function inquire_form_admin_form($form, &$form_state) {
   $form['inquire_form_thanks_nid'] = array(
     '#type' => 'textfield',
     '#title' => t('Node ID to Redirect to on Submit'),
     '#default_value' => variable_get('inquire_form_thanks_nid', FALSE),
     '#autocomplete_path' => 'unique_node_autocomplete_callback'
   );
   return system_settings_form($form);
 }

 function inquire_form_unique_node_autocomplete_callback($string = "") {
   $matches = array();
   if ($string) {
     $result = db_select('node')
       ->fields('node', array('nid', 'title'))
       ->condition('title', db_like($string) . '%', 'LIKE')
       ->range(0, 10)
       ->execute();
     foreach ($result as $node) {
       $matches[$node->title . " [$node->nid]"] = check_plain($node->title);
     }
   }
   drupal_json_output($matches);
 }
