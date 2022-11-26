<?php

namespace App\Database\Seeds\API;

use CodeIgniter\Database\Seeder;
use DateTime;
use DateTimeZone;

class Logemail extends Seeder
{
    public function run()
    {
        $datetime = new DateTime('now', new DateTimeZone('America/Lima'));
        $data = [
            'description' => 'POR DEFECTO',
            'created_at'   => $datetime->format('Y-m-d H:i:s'),
            'updated_at'   => $datetime->format('Y-m-d H:i:s')
        ];
        $this->db->table('logemail')->insert($data);
    }
}
