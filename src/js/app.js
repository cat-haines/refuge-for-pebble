var RestroomRefuge = require("lib/refuge.js");

var refuge = new RestroomRefuge();

function getRestrooms(onSuccess, onError) {
  navigator.geolocation.getCurrentPosition(function(position) {
    var options = {
      "lat": position.coords.latitude,
      "lng": position.coords.longitude
    };

    refuge.getRestrooms(options, onSuccess, onError);
  }, function(error) {
    onError("Error getting current position");
  });
}


function onAppReadyEvent(event) {
  // Indicate we're ready to go!
  getRestrooms(function(data) {
    var msg = {
      "dataNumPackets": 0,
      "data": []
    };

    data = data.filter(function(el) {
      // Only return resroom within 2.56 miles
      return el.distance < 2.56;
    }).filter(function(value, index, self) {
      // Only return unique restrooms
      return self.indexOf(value) === index;
    }).sort(function(a,b) {
       // Sort by distance
      return a.distance - b.distance;
    }).forEach(function(data) {
      if (msg.dataNumPackets < 10) {
        // Increment total number of locations
        msg.dataNumPackets++;
        // Figure out the size of this packet and add it to dataLength
        var locationName = data.name.length < 31 ? data.name : data.name.substring(0, 31);

        msg.data.push(Math.floor(data.distance * 100));
        msg.data.push(locationName.length);
        msg.data.push(locationName);
      }
    });
    if (msg.dataNumPackets > 0) {
      console.log(JSON.stringify(msg));
      Pebble.sendAppMessage(msg);
    } else {
      console.log("No data!");
    }

  }, function(err) {
    Pebble.sendAppMessage({ "noLocation": 1 });
  });
}

function onReady(event) {
  Pebble.sendAppMessage({ "appReady": 1 });
}

function onAppMessage(event) {
  if(event.payload.appReady) onAppReadyEvent(event);
}

Pebble.addEventListener('ready', onReady);
Pebble.addEventListener('appmessage', onAppMessage);
