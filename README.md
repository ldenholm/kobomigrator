# Info

This is a simple program which scans a directory for sub directories and copies across enclosed files. 
The program makes use of the std::filesystem library and constructs a map of filepaths when it locates
a candidate file. Specifically it looks for: epub, mobi, pdf, and azw3 formats. Update the 'fpath' and
'migration_dir' variables to your desired values, note these are relative paths to the directory in which
you execute the binary. Todo: accept user input for desired kobo path and migration path.
