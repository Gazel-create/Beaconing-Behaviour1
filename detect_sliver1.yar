rule Sliver_Ubuntu_Implant1{

	meta:
		author = "Gazel"
		description = "Detects Sliver C2 protobuf"
	
	strings:
		// Define your variables here.
		// YARA string variables always start with a $
		$protobuf = "sliverpb"
		$camo_url_1 = "samples.html"
		$camo_url_2 = "jquery.js"
	
	condition:
//This is where to set the trigger logic
//For this spring, we want it to trigger ifit sees any of these strings.
	$protobuf or $camo_url_1 or $camo_url_2

}
