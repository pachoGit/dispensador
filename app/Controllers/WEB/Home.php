<?php

namespace App\Controllers\WEB;

use App\Controllers\BaseController;

use App\Models\API\Config;
use App\Models\API\Detail;

class Home extends BaseController
{
    public function __construct()
    {
        $this->config = new Config;
        $this->detail = new Detail;
    }

    public function index()
    {
        $results = $this->detail
                 ->where('id_config', 1)
                 ->orderBy('time', 'ASC')
                 ->findAll();
        //echo var_dump($results);
        return view('dashboard', ['results' => $results]);
    }

    public function delete($id = null)
    {
        $this->detail->delete($id);
        return redirect()->to('web/home');
    }
}
