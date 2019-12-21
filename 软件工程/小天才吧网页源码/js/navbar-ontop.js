/**
 * navbar-ontop.js 1.0.0
 * Add .navbar-ontop class to navbar when the page is scrolled to top
 * Make sure to add this script to the <head> of page to avoid flickering on load
 */

(function() {

	var className = "navbar-ontop"
	
	// we start hidden, to avoid flickering
	document.write("<style id='temp-navbar-ontop'>.navbar {opacity:0; transition: none !important}</style>")

	function update() {
		// toggle className based on the scrollTop property of document
		var nav = document.querySelector(".navbar")

		if (window.scrollY > 30)
			nav.classList.remove(className)
		else
			nav.classList.add(className) 
	}

	document.addEventListener("DOMContentLoaded", function(event) {
		$(window).on('show.bs.collapse', function (e) {
			$(e.target).closest("." + className).removeClass(className);
		})

		$(window).on('hidden.bs.collapse', function (e) {
			update()
		})
		update()
		// still hacking to avoid flickering
		setTimeout(function() {
			document.querySelector("#temp-navbar-ontop").remove()
		})
  	});

	window.addEventListener("scroll", function() {
		update()			
	})

})();