<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Change password"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        
            
        if (empty($_POST["username"]) || empty($_POST["password"]))
        {
            apologize("Invalid registration details.");
        }
        if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Password and confirmation do not match.");
        }
        
        // Store the new user
        $success = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)",
            $_POST["username"], 
            password_hash($_POST["password"],
            PASSWORD_DEFAULT));
        
        // Log in the new user
        if ($success) {
            $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
            $_SESSION["id"] = $id;
        } else {
            apologize("Registration failed.");
        }
        
        // redirect to portfolio
        redirect("/");
    }

?>

