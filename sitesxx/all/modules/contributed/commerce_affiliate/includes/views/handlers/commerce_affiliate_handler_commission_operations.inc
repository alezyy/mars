<?php

/**
 * Field handler to present operations from contextual links.
 */
class commerce_affiliate_handler_commission_operations extends views_handler_field {
  function render($values) {
    $commission_id = $this->get_value($values);
    $router_item = current_path();

    $links = menu_contextual_links('commerce-affiliate-commission', $router_item, array($commission_id));
    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
