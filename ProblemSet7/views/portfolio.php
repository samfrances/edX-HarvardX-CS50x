
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
        </tr>

    <?php endforeach ?>
    </tbody>
</table>
<?php endif ?>

<p>Current cash balance: $<?= number_format($balance, 2) ?></p>
