<?php

namespace App\Database\Migrations\API;

use CodeIgniter\Database\Migration;

class Logemail extends Migration
{
    public function up()
    {
        $this->forge->addField([
            'id_logemail' => [
                'type'           => 'INT',
                'constraint'     => 5,
                'unsigned'       => true,
                'auto_increment' => true
            ],
            'description' => [
                'type'       => 'VARCHAR',
                'constraint' => '50',
                'null'       => true
            ],
            'created_at' => [
                'type' => 'DATETIME',
                'null' => true
            ],
            'updated_at' => [
                'type' => 'DATETIME',
                'null' => true
            ],
            'deleted_at' => [
                'type' => 'DATETIME',
                'null' => true
            ],

        ]);
        $this->forge->addKey('id_logemail', true);
        $this->forge->createTable('logemail');

    }

    public function down()
    {
        $this->forge->dropTable('logemail');
    }
}
