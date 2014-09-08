<?php

/**
 * Main class for the Affiliate campaign entity type.
 */
class AffiliateCampaign extends Entity {
  /**
   * Displayed in the statistics pages to identify the campaign.
   * 
   * @var string
   */
  public $name = '';
  
  /**
   * UID of the campaign owner. 0 if the campaign is global (available to all affiliates).
   * 
   * @var int
   */
  public $affiliate_uid = 0;
  
  /**
   * Whether this is the default campaign (used when no campaign is specified in the URL).
   * 
   * @var bool
   */
  public $is_default = FALSE;
  
  /**
   * Whether the campaign is still active (can accept clicks).
   * 
   * @var bool
   */
  public $is_active = TRUE;
  
  public function __construct(array $values = array(), $entityType = NULL) {
    parent::__construct($values, 'affiliate_campaign');
  }
  
  public function save() {
    $this->changed = REQUEST_TIME;
    if (!empty($this->is_new) && empty($this->created)) {
      $this->created = REQUEST_TIME;
    }
    
    parent::save();
  }
}
