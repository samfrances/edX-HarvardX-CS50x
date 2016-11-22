<?php

    // configuration
    require("../includes/config.php"); 
    
    // Put together shares info rows
    $transactions = CS50::query("SELECT timestamp, action, symbol, shares, price FROM history WHERE user_id = ? ORDER BY timestamp DESC", $_SESSION["id"]);
    if (count($transactions) == 0) {
        apologize("No transactions recorded.");
    }

    // render portfolio
    render("history.php", ["title" => "Transaction history", "transactions" => $transactions]);

?>
