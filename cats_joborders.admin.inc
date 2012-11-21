<?php

/**
 * Administrative settings form.
 */
function cats_joborders_settings_form($form, &$form_state) {
  $form = array();
  $form['cats_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('CATS settings'),
  );
  $form['cats_settings']['cats_url'] = array(
    '#type' => 'textfield',
    '#title' => t('CATS site URL'),
    '#description' => t('CATS index.php URL'),
    '#default_value' => variable_get('cats_url', ''),
  );
  $form['cats_settings']['cats_login'] = array(
    '#type' => 'textfield',
    '#title' => t('CATS site login'),
    '#description' => t('User login to CATS website'),
    '#default_value' => variable_get('cats_login', ''),
  );
  $form['cats_settings']['cats_password'] = array(
    '#type' => 'textfield',
    '#title' => t('CATS site password'),
    '#description' => t('User password to CATS website'),
    '#default_value' => variable_get('cats_password', ''),
  );
  $form['cats_settings']['cats_company_id'] = array(
    '#type' => 'textfield',
    '#title' => t('CATS company ID'),
    '#description' => t('Your CATS company ID'),
    '#default_value' => variable_get('cats_company_id', ''),
  );
  $form['http_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('HTTP settings'),
  );
  $form['http_settings']['cats_http_auth'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use HTTP auth'),
    '#default_value' => variable_get('cats_http_auth', 0),
  );
  $form['http_settings']['cats_http_auth_user'] = array(
    '#type' => 'textfield',
    '#title' => t('HTTP username'),
    '#default_value' => variable_get('cats_http_auth_user', ''),
  );
  $form['http_settings']['cats_http_auth_pass'] = array(
    '#type' => 'textfield',
    '#title' => t('HTTP password'),
    '#default_value' => variable_get('cats_http_auth_pass', ''),
  );
  return system_settings_form($form);
}

/**
 * Module actions form.
 */
function cats_joborders_actions_form($form, &$form_state) {
  $form = array();
  $form['actions'] = array(
    '#title' => t('Action'),
    '#type' => 'radios',
    '#options' => array(
      'get_form' => t('Get apply form structure'),
      'get_joborders' => t('Get joborders'),
    ),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

/**
 * Module actions form submit handler.
 */
function cats_joborders_actions_form_submit($form, &$form_state) {
  switch ($form_state['values']['actions']) {
    case 'get_form':
      cats_joborders_get_form_structure();
      break;
    case 'get_joborders':
      cats_joborders_get_orders();
      break;
  }
}
