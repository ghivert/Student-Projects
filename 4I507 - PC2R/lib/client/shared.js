'use strict'

let values = {
  'user'  : null,
  'client': null,
  'board' : [],
  'round' : 0,
  'enigma': {
    'red'   : {
      'x': 0,
      'y': 0
    },
    'blue'  : {
      'x': 0,
      'y': 0
    },
    'yellow': {
      'x': 0,
      'y': 0
    },
    'green' : {
      'x': 0,
      'y': 0
    },
    'target': {
      'x': 0,
      'y': 0
    },
    'color' : null
  },
  'opponents': {},
  'solution': [],
  'state': "WAIT"
}

exports.values = values
