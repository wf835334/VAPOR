add_library (render SHARED
	BarbRenderer.cpp
	ControlExecutive.cpp
	HelloRenderer.cpp
	Renderer.cpp
	ShaderMgr.cpp
	ShaderProgram.cpp
	TwoDDataRenderer.cpp
	TwoDRenderer.cpp
	GeoTile.cpp
	GeoTileMercator.cpp
	GeoTileEquirectangular.cpp
	GeoImage.cpp
	GeoImageTMS.cpp
	GeoImageGeoTiff.cpp
	ImageRenderer.cpp
	Visualizer.cpp
	VizFeatureRenderer.cpp
	jfilewrite.cpp
	textRenderer.cpp
	ControlExecutive.cpp
	ContourRenderer.cpp
)

target_link_libraries (render PUBLIC common vdc params ftgl freetype geotiff jpeg tiff)

if (NOT WIN32)
	target_compile_options(render PRIVATE "-Wno-deprecated-declarations")
endif ()

add_definitions (-DRENDER_EXPORTS)

install (
	TARGETS render
	DESTINATION ${INSTALL_LIB_DIR}
	COMPONENT Libraries
	)
