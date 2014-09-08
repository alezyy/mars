<?php

/**
 * Used for filtering click views by campaign, in the view title shows the campaign name
 * instead of the campaign id.
 */
class affiliate_ng_handler_argument_campaign extends views_handler_argument_string {
  function title() {
    $campaign = entity_load_single('affiliate_campaign', $this->argument);
    if (!$campaign) {
      return FALSE;
    }

    return $campaign->name;
  }
}