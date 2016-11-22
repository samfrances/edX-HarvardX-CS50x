<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("quote_form.php", ["title" => "Get quote"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (!isset($_POST["symbol"]) || $_POST["symbol"] == "")
        {
            apologize("No stock symbol provided.");    
        }
        $stock = lookup($_POST["symbol"]);
        if (!$stock)
        {
            apologize("Invalid stock symbol");
        }
        
        render("quote_info.php", ["title" => "Quote", "stock" => $stock]);
    }

?>