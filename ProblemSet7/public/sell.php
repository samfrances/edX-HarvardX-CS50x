<?php

    // configuration
    require("../includes/config.php"); 
    
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        if (!empty($_POST["symbol"])) {
            $symbol = $_POST["symbol"];
            $price = lookup($symbol)["price"];
            
            CS50::query("START TRANSACTION");
            
            $rows = CS50::query(
                "SELECT shares FROM portfolios where user_id = ? AND symbol = ?",
                $_SESSION["id"],
                $symbol
            );
            
            if (count($rows) != 1) {
                apologize("Oops, something went wrong looking up the number of shares.");
            }
            
            $shares = $rows[0]["shares"];
            
            CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $symbol);
            CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?;", $price * $shares, $_SESSION["id"]);
            
            // Record transaction
            CS50::query(
                "INSERT INTO history (user_id, symbol, shares, price, action) VALUES(?, ?, ?, ?, ?)",
                $_SESSION["id"],
                $symbol,
                $shares,
                $price,
                "sell"
            );
            
            $results = CS50::query("COMMIT");
            
            redirect("/sell.php");
        }
    }
    
    else if ($_SERVER["REQUEST_METHOD"] == "GET") {
        
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
        render("sell.php", ["title" => "Sell", "positions" => $positions, "balance" => $balance]);
        
    }
?>
