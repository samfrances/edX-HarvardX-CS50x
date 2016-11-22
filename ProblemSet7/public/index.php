<?php

    // configuration
    require("../includes/config.php"); 
    
    // Put together shares info rows
    $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    $positions = array();
    foreach ($rows as $row) {
        $stock = lookup($row["symbol"])["price"];
        if ($stock !== false) {
            $positions[] = array(
                "symbol" => $row["symbol"],
                "shares" => $row["shares"],
                "price" => $stock
            );
        }
    }
    
    // retrieve balance
    $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $balance = $rows[0]["cash"];

    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "balance" => $balance]);

?>
