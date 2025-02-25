<?php
// Copyright 2020 Catchpoint Systems Inc.
// Use of this source code is governed by the Polyform Shield 1.0.0 license that can be
// found in the LICENSE.md file.
if (!isset($WptHooks))
  $WptHooks = array();

LoadPlugins();

function LoadPlugins() {
  if (is_dir('./plugins')) {
    $plugins = glob('./plugins/*.inc');
    if ($plugins) {
      foreach($plugins as $plugin) {
        if (is_file($plugin))
          include_once($plugin);
      }
    }
  }
}

function WptAddHook($hook, $fn) {
  global $WptHooks;
  if (!array_key_exists($hook, $WptHooks))
    $WptHooks[$hook] = array();
  $WptHooks[$hook][] = $fn;
}  

function WptHookValidateTest(&$test) {
  global $WptHooks;
  $valid = true;
  if (array_key_exists('ValidateTest', $WptHooks)) {
    foreach ($WptHooks['ValidateTest'] as $fn) {
      $valid = call_user_func_array($fn, array(&$test));
      if (!$valid)
        break;
    }
  }
  return $valid;
}

function WptHookPostProcessResults($testPath) {
  global $WptHooks;
  if (array_key_exists('PostProcessResults', $WptHooks)) {
    foreach ($WptHooks['PostProcessResults'] as $fn) {
      call_user_func($fn, $testPath);
    }
  }
}
?>
