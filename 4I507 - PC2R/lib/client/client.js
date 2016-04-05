'use strict'

const net     = require('net')
const values  = require('./shared.js').values
const procDat = require('./processing.js').processData
const unco    = require('./processing.js').unconnect

exports.connect = function() {
  try {
    values.client = net.connect({ port: 2016 }, function () {
      try {
        values.client.write('CONNEXION/' + values.user + '/\n')
      } catch (err) {
        throw err
      }
    })
  } catch (err) {
    throw err
  }

  try {
    values.client.on('data', procDat)
  } catch (err) {
    console.log(err)
    throw err
  }
}

exports.unconnect = function() {
  unco()
}
