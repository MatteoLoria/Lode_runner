CC = g++

CFLAGS = -lallegro -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec

TARGET = LodeRunner

all: $(TARGET)

$(TARGET) : *.cpp
	 	$(CC) $(CFLAGS) -o $(TARGET) *.cpp

clean: 
 $(RM) $(TARGET)
