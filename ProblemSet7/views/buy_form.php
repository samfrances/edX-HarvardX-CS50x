<form action="buy.php" method="post">
    <fieldset>
        <div class="form-group">
            <input class="form-control" name="symbol" placeholder="Symbol" />
        </div>
        <div class="form-group">
            <input class="form-control" name="shares" placeholder="Number of shares" />
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-euro"></span>
                Buy
            </button>
        </div>
    </fieldset>
</form>
<p>Current cash balance: $<?= number_format($balance, 2) ?></p>