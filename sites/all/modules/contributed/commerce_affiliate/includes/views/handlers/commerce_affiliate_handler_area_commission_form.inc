<?php

/**
 * Defines a handler area that provides a form to add new commissions.
 */
class commerce_affiliate_handler_area_commission_form extends views_handler_area {
  function init(&$view, &$options) {
    parent::init($view, $options);
  }

  function render($empty = FALSE) {
    $parent_entity_id = $this->view->argument['parent_entity_id']->get_value();
    $parent_entity_type = $this->view->argument['parent_entity_type']->get_value();
    // No arguments provided, the view is probably being previewed. Abort.
    if (empty($parent_entity_id) || empty($parent_entity_type)) {
      return;
    }

    $parent_entity = entity_load_single($parent_entity_type, $parent_entity_id);
    // If there's an argument on the commission type, limit the add commission form
    // to that type alone.
    $commission_type = NULL;
    if (isset($this->view->argument['type'])) {
      $commission_type = $this->view->argument['type']->get_value();
    }

    module_load_include('inc', 'commerce_affiliate', 'includes/commerce_affiliate.forms');

    $content = drupal_get_form('commerce_affiliate_commission_add_form', $parent_entity_type, $parent_entity, $commission_type);
    return drupal_render($content);
  }
}
