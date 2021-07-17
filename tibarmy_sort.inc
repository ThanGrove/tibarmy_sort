<?php

define("TIB_SORT_FIELD_NAME", 'field_tibsortval'); // If this value is changed, must change also in tibarmy_sort.uninstall
define("TIB_SORT_FIELD_LABEL", 'Tibetan Sort Value');

include_once 'WordGranules.php';

function tibarmy_sort_field_add(&$node) {
  // watchdog('tibarmy_sort', "adding tib sort field from inc");
  if ($node->type != 'notice') { return; }
  $tibtitle = $node->title;
  // If not Tibetan, does nothing. Is this what we want? Or should the string itself get added to the Tib sort?
  if (!contains_tibetan($tibtitle)) {
    return;
  }
  #split key by word
  $wordArray=mb_split("་", $tibtitle);
  $reordVal="";
  foreach ($wordArray as $eachWord) {
    $wordClass=new WordGranules();
    if (mb_strlen($eachWord) > 0) {
      $reordVal .= $wordClass->getOrderedParts($eachWord);
    }
  }
  $node->{TIB_SORT_FIELD_NAME}['und'][0]['value'] = $reordVal;
}


/**
 * Function to check that string contains some tibetan
 *
 * @param $txt
 * @return bool
 */
function contains_tibetan($txt): bool
{
  $chars = tib_char_split($txt);
  foreach ($chars as $ch) {
    $chval = mb_ord($ch);
    if ($chval > 3839 && $chval < 4096) {
      return TRUE;
    }
  }
  return FALSE;
}


/**
 * A function to imitated mb_str_split which is only available in PHP 7.4
 * Site is currently running PHP 7.3
 *
 * @param $txt
 * @return array
 */
function tib_char_split($txt) {
  $chars = array();
  $txtlen = mb_strlen($txt);
  foreach(range(0, $txtlen) as $n) {
    $char = mb_substr($txt, $n, 1);
    if (!empty($char)) {
      $chars[] = $char;
    }
  }
  return $chars;
}
