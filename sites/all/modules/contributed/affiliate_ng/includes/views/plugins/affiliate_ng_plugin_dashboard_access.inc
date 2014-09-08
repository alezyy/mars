<?php

/**
 * Access plugin used for Affiliate Center views.
 */
class affiliate_ng_plugin_dashboard_access extends views_plugin_access {
  function access($account) {
    return affiliate_ng_dashboard_access($account);
  }

  function get_access_callback() {
    return array('affiliate_ng_dashboard_access', array(1));
  }

  function summary_title() {
    return t('Affiliate Center');
  }
}
