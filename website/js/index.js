var SpeechRecognition = SpeechRecognition || webkitSpeechRecognition
var SpeechGrammarList = SpeechGrammarList || webkitSpeechGrammarList
var SpeechRecognitionEvent = SpeechRecognitionEvent || webkitSpeechRecognitionEvent

var speech_sample = new SpeechRecognition();
speech_sample.lang = 'en-AU';
speech_sample.interimResults = false;
speech_sample.maxAlternatives = 1;

var feedback = document.querySelector('.output');
console.log(document.getElementById("textbox").value);

function speech_recognise() {
  speech_sample.start();
  console.log('Ready to receive audio.');
}

speech_sample.onresult = function(event) {
  var last = event.results.length - 1;
  var text_to_post = event.results[last][0].transcript;

  console.log(text_to_post);
  feedback.textContent = 'Result received: ' + text_to_post;
  console.log('Confidence: ' + event.results[0][0].confidence);

  submission(text_to_post);
}

speech_sample.onspeechend = function() {
  speech_sample.stop();
}

speech_sample.onerror = function(event) {
  feedback.textContent = 'Error occurred in recognition: ' + event.error;
}

function submix_textbox() {
    submission(document.getElementById("textbox").value)
}

function submission(text) {
  var xhttp = new XMLHttpRequest();

  var string_tail = text;
  var submission = 'args=' + string_tail;

  xhttp.open("POST", "https://api.particle.io/v1/devices/29002b001647363335343834/apimessage?access_token=282670953186db150e1f87ec217711d8a1b9104b", true);
  xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
  xhttp.send(submission);
}