const express = require('express');
const app = express();
const logger = require('morgan');
const http = require('http');
const path = require('path');
const PORT = process.env.PORT || 8080;
const bodyParser = require('body-parser');
const baseAPI = '/api/v1';
const sensorsService = require('./routes/sensors-service');
const sensors = require('./routes/sensors');
const cors = require('cors');

app.use(bodyParser.json());
app.use(logger('dev'));
app.use(bodyParser.urlencoded({
    extended: true
}));

app.use(cors());
app.use('/sensors', sensors);       // Servicios de base de datos con MongoDB

const server = http.createServer(app);

// Inicialización del servidor con conexión a MongoDB
sensorsService.connectDb(function (err) {
    if (err) {
        console.log('Could not connect with MongoDB – sensorsService');
        process.exit(1);
    }

    server.listen(PORT, function () {
        console.log('Server up and running on localhost:' + PORT);
    });
});
