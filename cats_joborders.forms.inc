<?php

/**
 * Job order apply form implementation.
 */
function cats_joborders_apply_form($form, &$form_state, $joborder_id) {
  $query = db_select('cats_joborders');
  $query->fields('cats_joborders', array('joborder_id', 'title', 'description'));
  $query->condition('joborder_id', $joborder_id);
  $joborder = $query->execute()->fetchAll();
  if (empty($joborder)) {
    $form = array();
    $form['message'] = array(
      '#markup' => t('Joborder not found'),
      '#weight' => -5,
    );
    return $form;
  }

  $form_state['joborder_id'] = $joborder_id;
  function objectToArray( $object )
    {
        if( !is_object( $object ) && !is_array( $object ) )
        {
            return $object;
        }
        if( is_object( $object ) )
        {
            $object = get_object_vars( $object );
        }
        return array_map( 'objectToArray', $object );
    }
  $form =objectToArray(variable_get('cats_form_structure', array())); 
        $form['joborder_fieldset'] = array(
            '#type' => 'fieldset',
            '#title' => t('Additional settings'),
            '#collapsible' => TRUE, 
            '#collapsed' => TRUE,
            '#theme' => 'joborder_fieldset_set',
        );
  
        $form['joborder_fieldset']['address'] = array(
            '#type' => 'textarea',
            '#title' => 'Address:',
        );
        $form['joborder_fieldset']['currentEmployer'] = array(
            '#type' => 'textfield',
            '#title' => 'Current Employer:',
        );
        $form['joborder_fieldset']['currentTitle'] = array(
            '#type' => 'textfield',
            '#title' => 'Current Title:',
        );
        $form['joborder_fieldset']['keySkills'] = array(
            '#type' => 'textfield',
            '#title' => 'Key Skills:',
        );
        $form['joborder_fieldset']['motherTongue'] = array(
            '#type' => 'textfield',
            '#title' => 'Mother Tongue:',
        );
        $form['joborder_fieldset']['birthDate'] = array(
            '#type' => 'textfield',
            '#title' => 'Birth Date:',
        );
        $form['joborder_fieldset']['file'] = array(
            '#type' => 'file',
            '#title' => 'Resume:',
            '#description' => 'Resume file in one of allowed formats (PDF, DOC).',
        );
  
//  $form['job_title'] = array(
//    '#type' => 'item',
//    '#title' => t($joborder[0]->title),
//    '#markup' => t($joborder[0]->description),
//    '#weight' => -5,
//  );
  $form['#attributes']['enctype'] = 'multipart/form-data';
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
  
}

/**
 * Job order apply form validation handler.
 */
function cats_joborders_apply_form_validate($form, &$form_state) {
  $validators = array(
    'file_validate_extensions' => array('doc pdf'),
  );
  $file = file_save_upload('file', $validators);
  if ($file) {
    $form_state['values']['file'] = '@' . drupal_realpath($file->uri);
  }
//  else {
//    form_set_error('file', t('Please, provide resume file in one of allowed formats (PDF, DOC).'));
//  }
}

/**
 * Job order apply form submit handler.
 */
function cats_joborders_apply_form_submit($form, &$form_state) {
  cats_joborders_post_apply($form_state['values'], $form_state['joborder_id']);
}
