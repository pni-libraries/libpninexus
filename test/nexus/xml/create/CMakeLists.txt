set(XML_FILES detector_data_file.xml
	          detector_master_file.xml
	          detector_link.xml
		  slit.xml
		  filters.xml
		  filters_mandatory.xml
	          duplicated_field.xml
	          duplicated_group.xml
	          detector_with_transformation.xml
	          simple_structure_with_data.xml
	          simple_structure.xml)
	         
foreach(XML_FILE ${XML_FILES})
	configure_file(${XML_FILE} ${XML_FILE} COPYONLY)
endforeach()
