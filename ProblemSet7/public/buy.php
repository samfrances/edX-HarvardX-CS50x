<?php

    // configuration
    require("../includes/config.php"); 
    
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        
        // Check if all correct info posted
        
        if (empty($_POST["symbol"])) {
            apologize("You must choose a symbol.");
        }
        
        if (empty($_POST["shares"])) {
           apologize("You must select how many shares you wish to buy.");
        }
        
        
        // Check if number of shares is whole number
        if (!preg_match("/^\d+$/", $_POST["shares"])) {
            apologize("You can only buy whole shares.");
        }
        
        $symbol = strtoupper($_POST["symbol"]);
        $shares = intval($_POST["shares"]);
        
        // Look up share info, and check requested share exists
        $share_info = lookup($symbol);
        if (!$share_info) {
            apologize("No such stock symbol on record.");
        }
        
        $price = $share_info["price"];

        CS50::query("START TRANSACTION");
        
        // retrieve balance
        $rows = CS50::query("SELECT cash FROM users WHERE id = ? FOR UPDATE", $_SESSION["id"]);
        $balance = $rows[0]["cash"];
        
        // Check the user has enough money
        if ($balance < ($shares * $price)) {
            CS50::query("ROLLBACK");
            apologize("Not enough cash.");
        }
        
        // Add shares to portfolio
        CS50::query(
            "INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",
            $_SESSION["id"],
            $symbol,
            $shares
        );
        
        // Deduct from balance
        CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?;", $price * $shares, $_SESSION["id"]);
        
        // Record transaction
        CS50::query(
            "INSERT INTO history (user_id, symbol, shares, price, action) VALUES(?, ?, ?, ?, ?)",
            $_SESSION["id"],
            $symbol,
            $shares,
            $price,
            "buy"
        );
        
        $results = CS50::query("COMMIT");
            
        redirect("/buy.php");
    }
    else if ($_SERVER["REQUEST_METHOD"] == "GET") {
        
        // retrieve balance
        $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $balance = $rows[0]["cash"];
        
        render("buy_form.php", ["title" => "Buy", "balance" => $balance]);    
    }

?>
