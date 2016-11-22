<?php if (count($positions) > 0): ?>
<table class="portfolio">
    <thead>
        <tr>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>        
    </thead>
    <tbody>

    <?php foreach ($positions as $position): ?>

        <tr>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td>$<?= number_format($position["price"], 4) ?></td>
            <td>
                <form action="sell.php" method="post">
                    <input type="hidden" name="symbol" value="<?= $position["symbol"] ?>">
                    <button class="btn btn-default" type="submit">
                    <span aria-hidden="true" class="glyphicon glyphicon-euro"></span>
                    Sell
                    </button>
                </form>
            </td>
        </tr>

    <?php endforeach ?>
    </tbody>
</table>
<?php else: ?>
<p>Nothing to sell.</p>
<?php endif ?>

<p>Current cash balance: $<?= number_format($balance, 2) ?></p>
