import pytsk3
import os

def recover_files(disk_image, output_directory):
    img_info = pytsk3.Img_Info(disk_image)
    filesystem = pytsk3.FS_Info(img_info)

    output_directory = os.path.abspath(output_directory)
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)

    for directory in filesystem.open_dir(path="/"):
        for file_entry in directory:
            file_name = file_entry.info.name.name.decode('utf-8', 'ignore')
            file_size = file_entry.info.meta.size

            # Specify the output path for the recovered file
            output_path = os.path.join(output_directory, file_name)

            with open(output_path, 'wb') as output_file:
                offset = 0
                while offset < file_size:
                    read_size = min(1024 * 1024, file_size - offset)
                    data = file_entry.read_random(offset, read_size)
                    output_file.write(data)
                    offset += read_size

if __name__ == "__main__":
    disk_image = "path/to/disk/image.dd"
    output_directory = "recovered_files_directory"

    recover_files(disk_image, output_directory)