$(document).ready(function () {
  console.log("I'm in a new file now.");
  // All JQuery code will be written here.

  //id selector
  $("#id1").click(function () {
    console.log("You clicked on an ID paragraph.");
  });

  //class selector
  $("#class1").click(function () {
    console.log("You clicked on a class paragraph.");
  });

  // element selector
  $("p").hover(function () {
    console.log("You mouseovered on p", this);
  });

  $("p").mousedown(function () {
    console.log("You clicked down on p", this);
  });

  $("p").mouseup(function () {
    console.log("You clicked up on p", this);
  });

  $("#para").hide(2000);
});
