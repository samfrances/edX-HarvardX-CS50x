<form action="change_password.php" method="post">
    <fieldset>
        <!-- Username not used, but prevents autocomplete -->
        <input type="text" name="username" value="" style="display:none">
        <div class="form-group">
            <input class="form-control" name="old_password" autocomplete="off" placeholder="Old Password" type="password"/><br>
        </div>
        <div class="form-group">
            <input class="form-control" name="new_password" placeholder="New Password" autocomplete="off" type="password"/><br>
            <input class="form-control" name="confirmation" placeholder="Confirmation" autocomplete="off" type="password"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Change Password
            </button>
        </div>
    </fieldset>
</form>
