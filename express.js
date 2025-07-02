const express = require('express');
const app = express();
const port = 3000;

app.get('/', (req, res) => {
  res.send('Hello World!');
});
app.static(express.static('public'));


app.listen(8080, () => {
  console.log(`Example app listening at http://localhost:${port}`);
});
