$url = 'http://www.htacg.org/binaries/binaries/tidy-5.1.8/tidy-5.1.8-win32.zip'
$url64bit = 'http://www.htacg.org/binaries/binaries/tidy-5.1.8/tidy-5.1.8-win64.zip'
$unzipLocation = "$(Split-Path -parent $MyInvocation.MyCommand.Definition)"

Install-ChocolateyZipPackage "packer" "$url" "$unzipLocation" "$url64bit"
