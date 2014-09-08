<?php

/**
 * Field handler to present operations from contextual links.
 */
class affiliate_ng_handler_field_campaign_name extends views_handler_field {
  function render($values) {
    $campaign_id = $this->get_value($values);
    $name = $this->get_value($values, 'name');


    // Is the view in the user pages, or in the admin pages?
    if (arg(0) == 'user') {
      $uid = arg(1);
      $router_item = 'user/'. $uid . '/affiliate/campaigns/' . $campaign_id;
    }
    else {
      $router_item = 'admin/affiliates/campaigns/' . $campaign_id;
    }

    return l($name, $router_item);
  }
}
