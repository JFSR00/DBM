'use strict';

const express = require('express');
const router = express.Router();
const sensorsService = require('./sensors-service');

router.get('/', function (req, res) {
    sensorsService.getAll((err, Sensor) => {
            if (err) {
                res.status(500).send({
                    msg: err
                });
            } else if (Sensor === null){
            	res.status(500).send({
                    msg: "Sensor null"
                });
            } else {
                res.status(200).send(Sensor);
            }
        }
    );
});

router.post('/', function (req, res) {
    let Sensor = req.body;
    sensorsService.add(Sensor, (err, Sensor) => {
            if (err) {
                res.status(500).send({
                    msg: err
                });
            } else if (Sensor !== null) {
                res.status(201).send({
                    msg: 'Sensor registrada'
                });
            }
        }
    );
});


router.delete('/', function (req, res) {
    sensorsService.removeAll((err) => {
        if (err) {
            res.status(500).send({
                msg: err
            });
        } else {
            res.status(200).send({
                msg: 'Sensor eliminada'
            });
        }
    });
});


router.get('/:_id', function (req, res) {
    let _id = req.params._id;
    sensorsService.get(_id, (err, Sensor) => {
            if (err) {
                res.status(500).send({
                	msg: err
            	});
            } else if (Sensor === null){
            	res.status(500).send({
                    msg: "sensors null"
                });
            } else {
                res.status(200).send(Sensor);
            }
        }
    );
});


router.put('/:_id', function (req, res) {
    const _id = req.params._id;
    const updatedSensor = req.body;
    sensorsService.update(_id, updatedSensor, (err, numUpdates) => {
        if (err || numUpdates === 0) {
            res.status(500).send({
                msg: err
            });
        } else {
            res.status(200).send({
                msg: 'Sensor Actualizada!'
            });
        }
    });
});

router.delete('/:_id', function (req, res) {
    let _id = req.params._id;
    sensorsService.remove(_id, (err) => {
        if (err) {
            res.status(500).send({
                msg: err
            });
        } else {
            res.status(200).send({
                msg: 'Sensor borrada!'
            });
        }
    });
});

module.exports = router;