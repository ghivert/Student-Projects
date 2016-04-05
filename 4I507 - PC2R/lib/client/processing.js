'use strict'

const shared = require('./shared.js')
const values = shared.values
var   chan

exports.unconnect = unconnect
function unconnect() {
  values.client.write('SORT/' + values.user + '/\n')
  values.client.end()
}

exports.processData = function(data) {
  chan = global.mainWindow.webContents
  // Get what the server tells.
  let input = data.toString('ascii').split(/\n|\//).filter((val) => {
    return val !== ''
  })
  console.error(input)
  // console.error(values)

  while (input.length > 0) {
    switch(input.shift()) {
      // Log in messages.
      case 'BIENVENUE': {
        if (input.shift() !== values.user) {
          console.error('Wrong user. What happend ?')
          try {
            unconnect()
          } catch (err) {
            console.log(err)
          }
          throw 'Wrong user.'
        }
        chan.send('add-opponent', values.user)
        break
      } case 'CONNECTE': {
        let name = input.shift()
        chan.send('add-opponent', name)
        values.opponents[name] = 0
        break
      } case 'DECONNEXION': {
        let name = input.shift()
        chan.send('delete-opponent', name)
        delete values.opponents[name]
        break
      } case 'SESSION': {
        stream = input.shift()
        readBoard()
        break
      } case 'VAINQUEUR': {
        readWinner(input.shift())
        break
      } case 'TOUR': {
        convertEnigma(input.shift())
        readWinner(input.shift())
        initBoard()
        values.state = "REFLEXION"
        break
      } case 'TUASTROUVE': {
        values.state = "ENCHERES"
        break
      } case 'ILATROUVE': {
        values.state = "ENCHERES"
        let user = input.shift()
        let moves = input.shift()
        values.solution.add([user, moves])
        chan.send('il-a-trouve', [user, moves])
        break
      } case 'FINREFLEXION': {
        values.state = "ENCHERES"
        chan.send('fin-reflexion')
        break
      } case 'VALIDATION': {
        console.log(input);
        break
      } case 'ECHEC': {
          chan.senc('echec', input.shift())
          break
      } case 'NOUVELLEENCHERE': {
        console.log(input);
        let user = input.shift()
        let moves = input.shift()
        chan.send('nouvelle-enchere', [user, moves])
        values.solution.push([user, moves])
        break
      } case 'FINENCHERE': {
        let user = input.shift()
        chan.send('fin-enchere', [user, input.shift()])
        if (user === values.user) {
          values.state = "SOLUTION"
        } else {
          values.state = "WAIT"
        }
        break
      } case 'SASOLUTION': {
        input.shift()
        chan.send('sa-solution', input.shift())
        break
      } case 'BONNE': {
        chan.send('bonne')
        break
      } case 'MAUVAISE': {
        let user = input.shift()
        chan.send('mauvaise', user)
        if (user === values.user) {
          values.state = "SOLUTION"
        } else {
          values.state = "WAIT"
        }
        break
      } case 'FINRESO': {
        values.state = "WAIT"
        values.solution = []
        break
      } case 'TROPLONG': {
        let user = input.shift()
        chan.send('trop-long', user)
        if (user === values.user) {
          values.state = "SOLUTION"
        } else {
          values.state = "WAIT"
        }
        break
      } case 'CHAT': {
        chan.send('chat', [input.shift(), input.shift()])
      }
    }
  }
}

var x, y, orient, stream

// Read a board state and fill the board variable with it.
function readBoard() {
  let walls = stream.split(/\(|\)|\,/).filter((val) => {
    return val !== ''
  })
  if (walls.length === 0) {
    console.error('No board... Why ?')
    try {
      unconnect()
    } catch (err) {
      console.log(err)
    }
    throw 'Wrong board.'
  }
  // Board is an array of tuples [x, y, orient] for each wall.
  while (walls.length !== 0) {
    x = walls.shift()
    y = walls.shift()
    orient = walls.shift()
    values.board.push([x, y, orient])
    paintWall()
  }
}

function paintWall() {
  let x1, x2, y1, y2
  switch (orient) {
    case "H": {
      x1 = (x - 1) * 40
      y1 = (y - 1) * 40
      x2 = (x - 1) * 40 + 40
      y2 = (y - 1) * 40
      break
    } case "B": {
      x1 = (x - 1) * 40
      y1 = (y - 1) * 40 + 40
      x2 = (x - 1) * 40 + 40
      y2 = (y - 1) * 40 + 40
      break
    } case "G": {
      x1 = (x - 1) * 40
      y1 = (y - 1) * 40
      x2 = (x - 1) * 40
      y2 = (y - 1) * 40 + 40
      break
    } case "D": {
      x1 = (x - 1) * 40 + 40
      y1 = (y - 1) * 40
      x2 = (x - 1) * 40 + 40
      y2 = (y - 1) * 40 + 40
      break
    }
  }
  chan.send('update-walls', [x1, y1, x2, y2])
}

// Read a end state and updates scores.
function readWinner(stream) {
  let score = stream.split(/\(|\)|\,/).filter((val) => {
    return val !== ''
  })

  if (score.length === 0) {
    console.error('No score... Why ?')
    try {
      unconnect()
    } catch (err) {
      console.log(err)
    }
    throw 'Wrong score.'
  }

  // Update the score of opponents.
  values.round = score.shift()
  while (score.length !== 0)
    values.opponents[score.shift()] = score.shift()
  chan.send('update-score')
}

// Convert the enigma.
function convertEnigma(stream) {
  let enigma = stream.split(/\(|\)|\,/).filter((val) => {
    return val !== ''
  })

  values.enigma.red.x    = enigma[0]
  values.enigma.red.y    = enigma[1]
  values.enigma.blue.x   = enigma[2]
  values.enigma.blue.y   = enigma[3]
  values.enigma.yellow.x = enigma[4]
  values.enigma.yellow.y = enigma[5]
  values.enigma.green.x  = enigma[6]
  values.enigma.green.y  = enigma[7]
  values.enigma.target.x = enigma[8]
  values.enigma.target.y = enigma[9]
  values.enigma.color    = enigma[10]
}

function initBoard() {
  chan.send('update-graphics',
    [
      values.enigma.red.x,    values.enigma.red.y,
      values.enigma.blue.x,   values.enigma.blue.y,
      values.enigma.yellow.x, values.enigma.yellow.y,
      values.enigma.green.x,  values.enigma.green.y,
      values.enigma.target.x,
      values.enigma.target.y,
      values.enigma.color
    ])
}
