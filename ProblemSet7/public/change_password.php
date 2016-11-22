<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("change_password_form.php", ["title" => "Change password"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // Validate presence of all required paramters
            
        if (empty($_POST["old_password"])) {
            apologize("You must supply your old password.");
        }
        
        if (empty($_POST["new_password"])) {
            apologize("You must supply a new password");
        }
        
        if (empty($_POST["confirmation"])) {
            apologize("You must confirm your new password.");
        }
        
        if ($_POST["new_password"] != $_POST["confirmation"])
        {
            apologize("Password and confirmation do not match.");
        }
        
        // Check that old password is correct
        
        // query database for user
        $rows = CS50::query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);

        // if we found user, check password
        if (count($rows) == 1)
        {
            // first (and only) row
            $row = $rows[0];

            // compare hash of user's input against hash that's in database
            if (!password_verify($_POST["old_password"], $row["hash"]))
            {
                apologize("Incorrect password");
            }
        }
        
        // Store the new password
        $success = CS50::query("UPDATE users SET hash = ? WHERE id = ?",
            password_hash($_POST["new_password"], PASSWORD_DEFAULT), 
            $_SESSION["id"]
        );
        
        // Log in the new user
        if (!$success) {
            apologize("Password change failed.");
        }
        
        // redirect to portfolio
        redirect("/");
    }

?>

