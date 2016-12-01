#!/usr/bin/env php
<?php

    $data_file_path = $argv[1];
    
    // Check that the file exists
    if (!file_exists($data_file_path)) {
        exit("Unable to find file: $data_file_path");
    }
    // Check that the file is readable
    if (!is_readable($data_file_path)) {
        exit("Unable to read file: $data_file_path");
    }
    
    $file = fopen($data_file_path, "r");
    while (($data = fgetcsv($file, 0, "\t")) !== FALSE) {
        CS50::query(
            "INSERT INTO places " . 
            "(country_code, " .
            "postal_code, " .
            "place_name, " .
            "admin_name1, " .
            "admin_code1, " .
            "admin_name2, " .
            "admin_code2, " .
            "admin_name3, " .
            "admin_code3, " .
            "latitude, " .
            "longitude, " .
            "accuracy) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
            $data[0], $data[1], $data[2], $data[3], $data[4], $data[5],
            $data[6], $data[7], $data[8], $data[9], $data[10], $data[11]
        );
    }
    fgetcsv($file, 0, "\t");
    fclose($file);

?>