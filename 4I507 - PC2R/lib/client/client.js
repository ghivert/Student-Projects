'use strict'

const net     = require('net')
const values  = require('./shared.js').values
const procDat = require('./processing.js').processData
const unco    = require('./processing.js').unconnect

exports.connect = function() {
  values.user = process.argv[2]

  try {
    values.client = net.connect({ port: 2016 }, function () {
      console.log('Connected !')
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
