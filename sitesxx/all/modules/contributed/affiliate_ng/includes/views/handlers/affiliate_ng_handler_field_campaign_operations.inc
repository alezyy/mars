<?php

/**
 * Field handler to present operations from contextual links.
 */
class affiliate_ng_handler_field_campaign_operations extends views_handler_field {
  function render($values) {
    $campaign_id = $this->get_value($values);
    $affiliate_uid = $this->get_value($values, 'affiliate_uid');
    $is_default = $this->get_value($values, 'is_default');

    // Is the view in the user pages, or in the admin pages?
    if (arg(0) == 'user') {
      $uid = arg(1);
      $router_item = "user/$uid/affiliate/campaigns";

      // Affiliates can't modify or delete global campaigns.
      if ($affiliate_uid == 0) {
        return;
      }
    }
    else {
      $router_item = 'admin/affiliates/campaigns';
    }

    $links = menu_contextual_links('affiliate-ng', $router_item, array($campaign_id));
    if (!empty($links)) {
      // Default campaigns can't be deleted.
      if ($is_default) {
        unset($links['affiliate-ng-delete']);
      }
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
