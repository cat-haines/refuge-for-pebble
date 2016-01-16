//**************** "LIBRARY" "CODE" ****************//
var RestroomRefuge = function(options) {
  // Defaults
  this.baseUrl = "http://www.refugerestrooms.org/api";
  this.locationUrl = "/v1/restrooms/by_location.json"

  this.unisex = false
  this.ada = false;

  // Allow dev to override defaults
  if (options) {
    if ("baseUrl" in options) this.baseUrl = options.baseUrl;
    if ("unisex" in options) this.unisex = options.unisex;
    if ("ada" in options) this.ada = options.ada;
  }

  // Returns nearby restroom
  this.getRestrooms = function(options, onSuccess, onError) {
    // Make sure we have required data
    if (!("lat" in options && "lng" in options)) {
      onError("No location data in search data");
      return;
    }

    // Grab optional parameters, or use defaults
    var unisexSearch = ("unisex" in options) ? options.unisex : this.unisex;
    var adaSearch = ("ada" in options) ? options.ada : this.ada;
    
    // Build the url + query string
    var requestUrl = this.baseUrl + this.locationUrl+ 
                     "?lat=" + options.lat + 
                     "&lng=" + options.lng +
                     "&ada=" + adaSearch + 
                     "&unisex=" + unisexSearch;

    // Setup our request
    var xhr = new XMLHttpRequest();
    xhr.onload = function () {
      if (this.status != 200) {
        onError("Error fetching restrooms (" + this.status + ")");
        return;
      }
      
      try {
        var data = JSON.parse(this.responseText)
        onSuccess(data);
      } catch (ex) {
        onError(ex);
      }
    };
    xhr.open("GET", requestUrl);
    xhr.send();
  };

}

//**************** APPLICATION CODE ****************//

var refuge = new RestroomRefuge();

function getRestrooms(onSuccess, onError) {
  navigator.geolocation.getCurrentPosition(function(position) {
    var options = {
      "lat": pos.coords.latitude,
      "lng": pos.coords.longitude
    };

    refuge.getRestrooms(options, onSuccess, onError);
  }, function(error) {
    onError("Error getting currnet position");
  });
}

function onReady(event) {
  Pebble.sendAppMessage({
    "ready": 0
  });
}

function onAppMessage(event) {

}

Pebble.addEventListener('ready', onReady);
Pebble.addEventListener('appmessage', onAppMessage);