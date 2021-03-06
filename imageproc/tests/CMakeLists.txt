INCLUDE_DIRECTORIES(BEFORE ..)

SET(
	sources
	main.cpp
	TestBinaryImage.cpp TestReduceThreshold.cpp
	TestSlicedHistogram.cpp
	TestConnCompEraser.cpp TestConnCompEraserExt.cpp
	TestGrayscale.cpp
	TestRasterOp.cpp TestShear.cpp
	TestOrthogonalRotation.cpp
	TestSkewFinder.cpp
	TestScale.cpp
	TestTransform.cpp
	TestMorphology.cpp
	TestDentFinder.cpp
	TestBinarize.cpp
	TestPolygonRasterizer.cpp
	TestKFill.cpp
	TestSeedFill.cpp
	TestSEDM.cpp
	TestLU.cpp
	TestLM.cpp
	Utils.cpp Utils.h
)
SOURCE_GROUP("Sources" FILES ${sources})

SET(
	libs
	imageproc math foundation ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	${Boost_PRG_EXECUTION_MONITOR_LIBRARY}
	${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY} ${EXTRA_LIBS}
)

ADD_EXECUTABLE(imageproc_tests ${sources})
TARGET_LINK_LIBRARIES(imageproc_tests ${libs})
