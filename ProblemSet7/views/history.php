
<table class="portfolio">
    <thead>
        <tr>
            <th>Timestamp</th>
            <th>Transaction</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price per share</th>
        </tr>        
    </thead>
    <tbody>

    <?php foreach ($transactions as $transaction): ?>

        <tr>
            <td><?= $transaction["timestamp"] ?></td>
            <td><?= $transaction["action"] ?></td>
            <td><?= $transaction["symbol"] ?></td>
            <td><?= $transaction["shares"] ?></td>
            <td>$<?= number_format($transaction["price"], 4) ?></td>
        </tr>

    <?php endforeach ?>
    </tbody>
</table>

