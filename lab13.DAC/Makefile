all:
	pio -f -c vim run

upload:
	pio -f -c vim run --target upload

clean:
	pio -f -c vim run --target clean

update:
	pio pkg update

compiledb:
	pio run -t compiledb
	mv compile_commands.json .vim/
