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

function onReady(event) {
  Pebble.sendAppMessage({ "appReady": 1 });

  // Indicate we're ready to go!
  getRestrooms(function(data) {
    // Pebble.sendAppMessage({ "washrooms": data });
  }, function(err) {
    // Pebble.sendAppMessage({ "noLocation": 1 });
  });
}

function onAppMessage(event) {

}

Pebble.addEventListener('ready', onReady);
Pebble.addEventListener('appmessage', onAppMessage);